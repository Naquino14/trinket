import Frame from './Frame'
import Defaults from './Defaults'

interface LCDProps {
    getFrames: () => Frame[],
    getDefaults: () => Defaults,
    setLine1: React.Dispatch<React.SetStateAction<string>>
    setLine2: React.Dispatch<React.SetStateAction<string>>
    setLcdColor: React.Dispatch<React.SetStateAction<string>>
}

let index = 0
const setindex = (i: number) => { index = i }
const getindex = () => { return index }

let stop = false
const stopStatus = () => { return stop }
const stopPlaying = () => {
    stop = true
    console.log(`stopPlaying: index=${index} stop=${stop}`)
}

let playing = false

const restart = () => {
    index = 0
    stop = false
    console.log(`restarting: index=${index} stop=${stop}`)
}

const sleep = (ms: number) => {
    if (ms < 0)
        return Promise.resolve()
    return new Promise(r => setTimeout(r, ms))
}

const playFrames = async ({ getFrames, getDefaults, setLine1, setLine2, setLcdColor }: LCDProps) => {
    console.log(`playFrames: index=${index}`)
    stop = false
    playing = true
    await sleep(getDefaults().startupTime)

    while (!stopStatus()) {
        const frames = getFrames()
        console.log(`playFrames: stop=${stop} index=${index} frames.length=${frames.length}`)
        for (let i = getindex(); i < getFrames().length; i++) {
            setindex(i)
            if (stopStatus()) {
                console.log(`playFrames: Stopping at index=${i}`)
                playing = false
                return Promise.resolve()
            }
            const frame = getFrames()[i]
            console.log(`playFrames frame: index=${i} duration=${frame.duration}`)
            setLine1(frame.line1)
            setLine2(frame.line2)
            setLcdColor(frame.color)
            await sleep(frame.duration)
        }
        index = 0
        await sleep(getDefaults().endTime)
    }
    playing = false
}

const stepFrame = ({ getFrames, getDefaults, setLine1, setLine2, setLcdColor }: LCDProps) => {
    const frames = getFrames()
    setindex(getindex() + 1 > frames.length - 1 ? 0 : getindex() + 1)
    const frame = frames[getindex()]
    setLine1(frame.line1)
    setLine2(frame.line2)
    setLcdColor(frame.color)
}

export { playFrames, stopPlaying, restart, stepFrame }
export default LCDProps