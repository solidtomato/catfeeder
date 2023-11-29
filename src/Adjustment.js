import React, { useState } from 'react'

const Adjustment = () => {
    const [sliderValue, setSliderValue] = useState(5)
    const [loading, setLoading] = useState(false)

    const handleSliderChange = (event) => {
        setSliderValue(event.target.value)
    }

    const handleSubmit = () => {
        setLoading(true)

        // 2 second delay
        setTimeout(() => {
            setLoading(false);
            console.log(`Slider Value: ${sliderValue}`)
            // Add your submission logic here
        }, 2000)
    };

    return (
        <div>
            {sliderValue}
            <input 
                type="range" 
                min="1" 
                max="10" 
                value={sliderValue} 
                onChange={handleSliderChange} 
            />
            <button onClick={handleSubmit} disabled={loading}>
                {loading ? 'Loading...' : 'Submit'}
            </button>
            {loading && <div className="spinner"></div>}
        </div>
    )
}

export default Adjustment