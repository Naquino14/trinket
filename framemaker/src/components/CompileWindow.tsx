import React from 'react'
import './CompileWindow.tsx.css'

interface CompileWindowProps {
    text: string
    setDisplayCompile: React.Dispatch<React.SetStateAction<boolean>>
}

const CompileWindow: React.FC<CompileWindowProps> = ({ text, setDisplayCompile }: CompileWindowProps) => {
    const [copyText, setCopyText] = React.useState('Copy')
    const [downloadText, setDownloadText] = React.useState('Download')

    return (
        <div className='compile-window'>
            <div className='compile-window_frame'>
                <div className='compile-label'>Compiled frames:</div>
                <div className='compile-textbox code'>{text}</div>
                <div className='compile-button_container'>
                    <button className='compile-button' onClick={(e) => {
                        e.preventDefault()
                        navigator.clipboard.writeText(text)
                        setCopyText('Copied!')
                    }} onMouseLeave={() => setCopyText('Copy')}>{copyText}</button>
                    <button className='compile-button' onClick={(e) => {
                        e.preventDefault()
                        const element = document.createElement('a')
                        const file = new Blob([text], { type: 'text/plain' })
                        element.href = URL.createObjectURL(file)
                        element.download = 'frames.ssv'
                        document.body.appendChild(element)
                        element.click()
                        setDownloadText('Downloaded!')
                    }} onMouseLeave={() => setDownloadText('Download')}>{downloadText}</button>
                    <button className='compile-button' onClick={() => setDisplayCompile(false)}>Close</button>
                </div>
            </div>
        </div>
    )
}

export default CompileWindow