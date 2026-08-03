import packer
import corruptor

print("How to use: Ensure that gd-directory is empty, and allowed-files.dat exists. Once the script starts corrupting, it will generate a .gddir file.")
print("You can ignore this, as it will corrupt the game using this file and put the result in the gd-directory folder. From there, you can run Geometry Dash.")
print("Any custom resources that aren't included in the original game are not corrupted, meaning you can transfer over Geode to pair this with the mod version.")
print("You need to own a copy of geometry dash to use this!")

print("Please enter the absolute path to your Geometry Dash directory. Please use regular slashes. (/)")
print("Leaving it blank will leave it to the default: C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash/")
pathx = input("")

if pathx == "":
    pathx = "C:/Program Files (x86)/Steam/steamapps/common/Geometry Dash/"

allowed_files = packer.read_allowed_files("allowed-files.dat")

with open("packed.gddir", "wb") as f:
    f.write(packer.pack_gd_dir(pathx, allowed_files))
packer.read_gd_dir("packed.gddir", allowed_files)
packer.unpack_gd_dir("packed.gddir", "./gd-directory/", allowed_files)

corruption_levelx = input("Please enter your corruption level (100 is the max, but you can go past it): ")

corrupted_gddir = corruptor.corrupt_gddir("packed.gddir", float(corruption_levelx) / 100)

with open("packed.gddir", "wb") as f:
    f.write(corrupted_gddir)
    f.flush()

    packer.unpack_gd_dir("packed.gddir", "", packer.read_allowed_files("allowed-files.dat"))

print("Corrupted! Enjoy")
print("Tip: Go to low texture quality for the most corruptions")