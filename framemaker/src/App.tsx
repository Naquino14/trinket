import React, { useState } from 'react'
import './App.tsx.css'
import LCD from './components/LCD'
import Button from './components/Button'

function App() {
  const [line1, setLine1] = useState('1234567891234567')
  const [line2, setLine2] = useState('123')
  const [lcdColor, setLcdColor] = useState('#fff')
  return (
    <div className='app'>
      <div className="header">
        <h1 className='title'>FRAMEMAKER</h1>
      </div>
      <div className='lcd-container'>
        <LCD line1={line1} line2={line2} color={lcdColor} />
        <Button label='PLAY' onclick={() => alert('play')} />
        <Button label='PAUSE' onclick={() => alert('pause')} />
        <Button label='RESTART' onclick={() => alert('restart')} />
        <Button label='STEP' onclick={() => alert('STEP')} />
      </div>
    </div>
  )
}

export default App
