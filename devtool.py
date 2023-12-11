import os
import sys
import subprocess

if __name__ == "__main__":
    subprocess.run(("./external/bin/premake/premake5.exe", "vs2022"))