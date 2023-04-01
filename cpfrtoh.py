#!/usr/bin/env python

import os
# turns frames.ssv into frames.h
def main():
    with open('frames.ssv') as f:
        lines = f.readlines()
    with open('frames.h', 'w') as f:
        f.write('const char *FRAMES = \"')
        for line in lines:
            f.write(line.strip() + '\\n')
        f.write('\";')
    os.system('cd ./build && make')
    return 0

if __name__ == '__main__':
    main()