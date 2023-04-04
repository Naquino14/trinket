#!/usr/bin/env python

import os
# turns frames.ssv into frames.h
def main():
    with open('frames.ssv') as f:
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
        f.write(f'#define FRAMES_LEN {c + 2}')
    os.system('cd ./build && make')
    return 0

if __name__ == '__main__':
    main()