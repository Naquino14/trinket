import React from 'react'
import Frame from '../Frame'
import './CharCounter.tsx.css'

interface CharCounterProps { line: string }

const CharCounter: React.FC<CharCounterProps> = ({ line }: CharCounterProps) => {
    return (
        <div className='charCounter'>
            <div>{line.length}</div>
            <div className='charCounter-separator' />
            <div>16</div>
        </div>
    )
}

export default CharCounter