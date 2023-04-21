import React from 'react'
import Frame from '../Frame'
import './FrameEditor.tsx.css'

interface FrameEditorProps {
    frame: Frame
    deleteFrame: (id: number) => void
    reorderFrame: (id: number, direction: number) => void
    updateFrame: (frame: Frame) => void
}

const FrameEditor: React.FC<FrameEditorProps> = ({ frame, deleteFrame, reorderFrame, updateFrame }) => {
    return (
        <div className='frameEditor' style={{
            borderTop: frame.id === 0 ? 'none' : '2px solid #777',
            borderTopLeftRadius: frame.id !== 0 ? '0' : '10px',
            borderTopRightRadius: frame.id !== 0 ? '0' : '10px',
            borderBottomLeftRadius: frame.id === 0 ? '0' : '10px',
            borderBottomRightRadius: frame.id === 0 ? '0' : '10px',
        }}>
            <div className='index code'>{frame.id}</div>
            <div className='reorder-buttons'>
                <button className='reorder-button' onClick={(e) => {
                    e.preventDefault()
                    reorderFrame(frame.id, -1)
                }} >▲</button>
                <button className='reorder-button' onClick={(e) => {
                    e.preventDefault()
                    reorderFrame(frame.id, 1)
                }} >▼</button>
            </div>
            <div className='separator' />
            <div className='parameter-container'>
                <div className='parameter'>Line 1:
                    <input type='text' value={frame.line1} defaultValue={frame.line1} onChange={(e) => {
                        e.preventDefault()
                        updateFrame({ ...frame, id: frame.id, line1: e.target.value })
                    }} /></div>
                <div className='parameter'>Line 2:
                    <input type='text' value={frame.line2} defaultValue={frame.line2} onChange={(e) => {
                        e.preventDefault()
                        updateFrame({ ...frame, id: frame.id, line2: e.target.value })
                    }}></input></div>
                <div className='parameter'>Color:
                    <input type='color' value={frame.color} defaultValue={frame.color} onChange={(e) => {
                        e.preventDefault()
                        updateFrame({ ...frame, id: frame.id, color: e.target.value })
                    }}></input></div>
                <div className='parameter'>Duration: {frame.duration}</div>
            </div>
            <button className='button' onClick={(e) => {
                e.preventDefault()
                deleteFrame(frame.id)
            }} >X</button>
        </div >
    )
}

export default FrameEditor