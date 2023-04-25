import Frame from './Frame'
import Defaults from './Defaults'

interface LCDProps {
    frames: Frame[],
    defaults: Defaults,
    setLine1: React.Dispatch<React.SetStateAction<string>>
    setLine2: React.Dispatch<React.SetStateAction<string>>
    setLcdColor: React.Dispatch<React.SetStateAction<string>>
}

let index = 0
const setindex = (i: number) => { index = i }
let stop = false
const stopPlaying = () => { stop = true }

const restart = () => {
    index = 0
    stop = false
}

const sleep = (ms: number) => { return new Promise(r => setTimeout(r, ms)) }

const playFrames = async ({ frames, defaults, setLine1, setLine2, setLcdColor }: LCDProps) => {
    await sleep(defaults.startupTime)

    while (!stop) {
        console.log(`playFrames: stop=${stop} index=${index} frames.length=${frames.length}`)
        for (let i = index; i < frames.length; i++) {
            setindex(i)
            const frame = frames[i]
            setLine1(frame.line1)
            setLine2(frame.line2)
            setLcdColor(frame.color)
            await sleep(frame.duration)
        }
        index = 0
        await sleep(defaults.endTime)
    }
}

export { playFrames, stopPlaying, restart }