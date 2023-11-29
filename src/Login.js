import React, { useState } from 'react'

function Login({ auth }) {
  const [username, setUsername] = useState('')
  const [password, setPassword] = useState('')

  const handleUsernameChange = (event) => {
    setUsername(event.target.value)
  }

  const handlePasswordChange = (event) => {
    setPassword(event.target.value)
  }


  /**
   * 
   * this is like really fucking stupid and bad security but hey i can't
   * be bothered and it doesn't really matter all that much and who would ever 
   * wanna fuck over some innocent cats who visit my backyard from time to time
   * they are just trynna survive and we are just helping them to get through the winter
   */
  const handleSubmit = (event) => {
    event.preventDefault();
    const creds = {
      'zoe': 'solidtomato',
      'harley': 'solidtomato'
    }
    
    if (creds[username] === password) {
      auth()
    } 
  }

  return (
    <form onSubmit={handleSubmit}>
      <div>
        <label htmlFor="username">Username:</label>
        <input
          type="text"
          id="username"
          value={username}
          onChange={handleUsernameChange}
        />
      </div>
      <div>
        <label htmlFor="password">Password:</label>
        <input
          type="password"
          id="password"
          value={password}
          onChange={handlePasswordChange}
        />
      </div>
      <button type="submit">Login</button>
    </form>
  );
}

export default Login
