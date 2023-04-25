import React, { useState } from 'react'
import './App.tsx.css'
import LCD from './components/LCD'
import Defaults from './Defaults'
import Frame from './Frame'
import FrameEditor from './components/FrameEditor'
import { playFrames, restart, stepFrame, stopPlaying } from './AnimationController'

function App() {
  const [line1, setLine1] = useState('')
  const [line2, setLine2] = useState('')
  const [lcdColor, setLcdColor] = useState('#ffffff')
  const [defaults, setDefaults] = useState<Defaults>({ color: '#ffffff', startupTime: 1000, frameTime: 1000, endTime: 1000 })
  const [frames, setFrames] = useState<Frame[]>([])

  const deleteFrame = (id: number) => {
    setFrames(frames.filter((frame) => frame.id !== id))
    for (let i = id + 1; i < frames.length; i++)
      frames[i].id = i - 1
  }

  const reorderFrame = (id: number, direction: number) => {
    // swap frames
    if (direction === 0)
      return
    const framesCopy = [...frames]
    if (direction === -1) {
      if (id === 0)
        return
      const temp = framesCopy[id]
      temp.id = id - 1
      framesCopy[id] = framesCopy[id - 1]
      framesCopy[id - 1] = temp
      framesCopy[id].id = id
    } else {
      if (id === framesCopy.length - 1)
        return
      const temp = framesCopy[id]
      temp.id = id + 1
      framesCopy[id] = framesCopy[id + 1]
      framesCopy[id + 1] = temp
      framesCopy[id].id = id
    }
    setFrames(framesCopy)
  }

  const updateFrame = (frame: Frame) => {
    setFrames(frames.map((f) => f.id === frame.id ? frame : f))
  }

  const getFrames = () => { return frames }
  const getDefaults = () => { return defaults }

  return (
    <div className='app'>
      <div className="header">
        <h1 className='title'>FRAMEMAKER</h1>
      </div>
      <div className='lcd-container'>
        <LCD line1={line1} line2={line2} color={lcdColor} />
      </div>
      <div className='button-container'>
        <button className='button' onClick={() => playFrames({ getFrames, getDefaults, setLine1, setLine2, setLcdColor })} >PLAY</button>
        <button className='button' onClick={() => stopPlaying()} >PAUSE</button>
        <button className='button' onClick={() => restart()} >RESTART</button>
        <button className='button' onClick={() => stepFrame({ getFrames, getDefaults, setLine1, setLine2, setLcdColor })} >STEP</button>
        <button className='button' onClick={() => { setFrames([]) }} >CLEAR</button>
      </div>
      <div className='frames-container_bg'>
        <div className='frames-container'>
          <form className='defaults-form' onSubmit={() => alert('submit')}>
            <label className='defaults-label'>Color:
              <input className='defaults-input' type='color' value={defaults.color} onChange={(e) => {
                setDefaults({ ...defaults, color: e.target.value })
              }
              } />
            </label>
            <label className='defaults-label'>
              Startup Time:
              <input className='defaults-input' type='number' value={defaults.startupTime} onChange={(e) => {
                e.preventDefault()
                setDefaults({ ...defaults, startupTime: parseInt(e.target.value) })
              }} />
            </label>
            <label className='defaults-label'>
              Frame Time:
              <input className='defaults-input' type='number' value={defaults.frameTime} onChange={(e) => {
                e.preventDefault()
                setDefaults({ ...defaults, frameTime: parseInt(e.target.value) })
              }} />
            </label>
            <label className='defaults-label'>
              End Time:
              <input className='defaults-input' type='number' value={defaults.endTime} onChange={(e) => {
                e.preventDefault()
                setDefaults({ ...defaults, endTime: parseInt(e.target.value) })
              }} />
            </label>
          </form>
          <div className='defaults-separator' />
          <div className='frames'>
            {
              frames.map((frame, index) => {
                return (
                  <FrameEditor frame={frame} key={index} deleteFrame={deleteFrame} reorderFrame={reorderFrame} updateFrame={updateFrame} />
                )
              })
            }
          </div>
          <button className='addframe-button' onClick={(e) => {
            e.preventDefault()
            setFrames([...frames, { id: frames.length, color: defaults.color, line1: '', line2: '', duration: defaults.frameTime }])
          }}>+</button>
        </div>
      </div>
    </div >
  )
}

export default App
