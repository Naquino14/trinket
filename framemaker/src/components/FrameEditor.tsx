import React from 'react'
import Frame from '../Frame'
import './FrameEditor.tsx.css'

interface FrameEditorProps {
    frame: Frame
    deleteFrame: (id: number) => void
    reorderFrame: (id: number, direction: number) => void
    updateFrame: (frame: Frame) => void
    duplicateFrame: (id: number) => void
}

const FrameEditor: React.FC<FrameEditorProps> = ({ frame, deleteFrame, reorderFrame, updateFrame, duplicateFrame }) => {
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
                    <input className='parameter-input' type='text' value={frame.line1} onChange={(e) => {
                        e.preventDefault()
                        // check if the line is too long
                        if (e.target.value.length > 16) {
                            // if it is, set the value to the previous value
                            e.target.value = frame.line2
                            // and return
                            return
                        }
                        updateFrame({ ...frame, id: frame.id, line1: e.target.value })
                    }} /></div>
                <div className='parameter'>Line 2:
                    <input className='parameter-input' type='text' value={frame.line2} onChange={(e) => {
                        e.preventDefault()
                        if (e.target.value.length > 16) {
                            e.target.value = frame.line2
                            return
                        }
                        updateFrame({ ...frame, id: frame.id, line2: e.target.value })
                    }} /></div>
                <div className='parameter'>Color:
                    <input className='parameter-input' type='color' value={frame.color} onChange={(e) => {
                        e.preventDefault()
                        updateFrame({ ...frame, id: frame.id, color: e.target.value })
                    }} /></div>
                <div className='parameter'>Duration:
                    <input className='parameter-input' type='number' value={frame.duration} onChange={(e) => {
                        e.preventDefault()
                        updateFrame({ ...frame, id: frame.id, duration: parseInt(e.target.value) })
                    }} /></div>
            </div>
            <button className='button' onClick={(e) => {
                e.preventDefault()
                duplicateFrame(frame.id)
            }} >⩔</button>
            <button className='button' style={{ marginRight: '10px' }} onClick={(e) => {
                e.preventDefault()
                deleteFrame(frame.id)
            }} >X</button>
        </div >
    )
}

export default FrameEditor