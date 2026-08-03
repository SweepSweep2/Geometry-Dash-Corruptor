# Packing/unpacking

import pathlib
from concurrent.futures import ThreadPoolExecutor
import time


def read_allowed_files(path: str) -> set:
    print("Reading allowed files data...")

    return_list = []

    with open(path, "rb") as f:
        i = 0
        data = f.read()

        while i < len(data):
            length = int.from_bytes(data[i:i + 2], byteorder="little")
            p = data[i + 2:i + 2 + length].decode("ascii")

            i += 2 + length

            return_list.append(p)

    print("Successfully read allowed files data!")
    print("Allowed files: " + str(len(return_list)))

    return set(return_list)


def pack_gd_dir(path: str, allowed_files: set) -> bytes:
    print("Packing Geometry Dash directory...")

    matched = []

    for rel in allowed_files:
        f = pathlib.Path(path) / rel

        if f.is_file():
            matched.append(str(f.as_posix()))

    def read_file(a_file):
        with open(a_file, "rb") as fa:
            return fa.read()

    with ThreadPoolExecutor() as executor:
        results = executor.map(read_file, matched)

    print("Successfully packed Geometry Dash directory!")
    print("Generating .gddir file...")

    matched = []

    for rel in allowed_files:
        f = pathlib.Path(path) / rel

        if f.is_file():
            matched.append("gd-directory/" + str(f.as_posix())[len(path):])

    dictionary = dict(zip(matched, results))

    beginning = []
    chunks = []
    data_chunks = []

    header_length = 4

    for file, data in dictionary.items():
        chunks.append(len(file).to_bytes(2, "little"))
        chunks.append(len(data).to_bytes(4, "little"))
        chunks.append(file.encode("ascii"))

        header_length += 6 + len(file)

        data_chunks.append(data)

    beginning.append(header_length.to_bytes(4, "little"))

    return_bytes = b"".join(beginning + chunks + data_chunks)

    print("Generated .gddir file!")

    return return_bytes


def read_gd_dir(path: str, allowed_files: set) -> dict:
    print("Reading .gddir file...")

    with open(path, "rb") as f:
        data = f.read()

        files = {}
        i = 4
        i_2 = 0

        data_offset = int.from_bytes(data[0:4], byteorder="little")

        while i_2 < len(allowed_files):
            filename_size = int.from_bytes(data[i:i + 2], byteorder="little")
            file_size = int.from_bytes(data[i + 2:i + 6], byteorder="little")
            file_name = data[i + 6:i + 6 + filename_size].decode("ascii")

            i += 6 + filename_size

            file_data = data[data_offset:data_offset + file_size]
            data_offset += file_size
            files[file_name] = file_data

            i_2 += 1

    print("Successfully read .gddir file!")

    return files


def unpack_gd_dir(path: str, dest: str, allowed_files: set):
    print("Unpacking .gddir file...")

    files = read_gd_dir(path, allowed_files)

    for file, data in files.items():
        pathlib.Path(dest + file).parent.mkdir(parents=True, exist_ok=True)
       # print(pathlib.Path(file))
        #print(pathlib.Path(file).parent)

        with open(dest + file, "wb") as d:
            d.write(data)

    print("Successfully unpacked .gddir file!")


def dict_to_gd_dir(data: dict) -> bytes:
    beginning = []
    chunks = []
    data_chunks = []

    header_length = 4

    for file, adata in data.items():
        chunks.append(len(file).to_bytes(2, "little"))
        chunks.append(len(adata).to_bytes(4, "little"))
        chunks.append(file.encode("ascii"))

        header_length += 6 + len(file)

        data_chunks.append(adata)

    beginning.append(header_length.to_bytes(4, "little"))

    return b"".join(beginning + chunks + data_chunks)