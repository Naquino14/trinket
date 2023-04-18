import React from 'react'
import './Button.tsx.css'

interface ButtonProps {
    onclick: () => void
    label: string
}

const Button: React.FC<ButtonProps> = ({ label, onclick }) => {
    return (
        <button className='button' onClick={onclick}>{label}</button>
    )
}

export default Button