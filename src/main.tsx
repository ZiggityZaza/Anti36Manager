import * as os from "node:os"
import React from "react"
import * as ReactDOM from "react-dom/client"
import * as cs from "./cslib.js"
import * as bn from "./logic.js"



type html_t = React.ReactElement




function MyButton(): html_t {
  return (
    <button>I'm a button</button>
  );
}



function App(): html_t {
  console.log("Running app")
  const [count, set_count] = React.useState(1)

  if (count < 10)
    return (
      <div>
        <p>Button touched {count} times</p>
        <button onClick={() => set_count(count + 1)}>+</button>
        <button onClick={() => set_count(count - 1)}>-</button>
      </div>
    )
  else
    return (
      <div>
        <p>Enough pressing. <MyButton /></p>
      </div>
    )
}



window.onload = () => {
  document.getElementById("output")!.textContent = "Running on platform: " + os.platform()
  console.log(cs.is_windows())

  const root = ReactDOM.createRoot(document.getElementById("output")!)
  root.render(<App />)

  bn.letsGo()
};