
import Login from './Login';
import './App.css';
import { useState } from 'react';
import Adjustment from './Adjustment';

function App() {

  const [isLoggedIn, setIsLoggedIn] = useState(false)

  return (
    <div className="App">
      {isLoggedIn ? <Adjustment /> : <Login auth={() => setIsLoggedIn(true)}/>}
    </div>
  );
}

export default App;
