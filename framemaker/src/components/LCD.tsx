import React from "react"
import './LCD.tsx.css'

interface LCDProps {
    line1: string
    line2: string
    color: string
}

const LCD: React.FC<LCDProps> = ({ line1, line2, color }) => {
    return (
        <div className='led-backing'>
            <div className='lcd' style={{ backgroundColor: color }}>
                <div className='line code'>{line1}</div>
                <div className='line code'>{line2}</div>
            </div >
        </div>
    )
}

export default LCD