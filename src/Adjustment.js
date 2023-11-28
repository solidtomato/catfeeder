import React, { useState } from 'react';

const Adjustment = () => {
    const [sliderValue, setSliderValue] = useState(1);

    const handleSliderChange = (event) => {
        setSliderValue(event.target.value);
    };

    const handleSubmit = () => {
        // Handle the submission logic here
        console.log(`Slider Value: ${sliderValue}`);
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
            <button onClick={handleSubmit}>Submit</button>
        </div>
    );
};

export default Adjustment;
