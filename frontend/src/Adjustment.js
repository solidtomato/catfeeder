import React, { useState } from 'react'

const Adjustment = () => {
    const [sliderValue, setSliderValue] = useState(5)
    const [loading, setLoading] = useState(false)

    const handleSliderChange = (event) => {
        setSliderValue(event.target.value)
    }

    const handleSubmit = () => {
        setLoading(true)
        fetch(`http://192.168.68.65/${sliderValue - 1}`)
            .then((res) => console.log(res.status))
            .catch((err) => console.error(err))
            .finally(() => setLoading(false))
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