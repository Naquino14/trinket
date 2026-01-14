#!/usr/bin/env python3
# CoPy FRames TO Header

import os
import sys
import time
# turns frames.ssv into frames.h
def main(argc, argv):
    if argc != 2:
        print('Usage: cpfrtoh.py [file]')
        return 1
    with open(argv[1]) as f:
        lines = f.readlines()
    c = 0
    lc = 0
    with open('frames.h', 'w') as f:
        f.write('#define FRAMES \"')
        for line in lines:
            # write the line, with a newline if it's not the last line
            f.write(line.strip() if lc == len(lines) - 1 else line.strip() + '\\n')
            c += len(line)
            lc += 1
        f.write('\"\n')
        f.write(f"#define FRAMES_LEN {c + 2}")
    os.system('cd ./build && make')

    if "PICO_MOUNT_POINT" in os.environ:
        print("Waiting for pico to mount...")
            
        os.system("echo BOOT > /dev/ttyACM0")
        mp = os.environ["PICO_MOUNT_POINT"]
        while not os.path.exists(mp):
            if os.path.exists("/dev/ttyACM0"):
                os.system("echo BOOT > /dev/ttyACM0")
            time.sleep(250 / 1000)

        time.sleep(250 / 1000)  # wait a bit more

        os.system(f'cp ./build/trinket.uf2 {mp}')
    return 0

if __name__ == '__main__':
    main(len(sys.argv), sys.argv)