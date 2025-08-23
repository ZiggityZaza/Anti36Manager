// No need to manually have this ts as it has few instructions
import * as electron from 'electron'
import * as path from 'path'
import * as url from 'url'
const createWindow = () => {
  const thisFilename = url.fileURLToPath(import.meta.url)
  const mainWindow = new electron.BrowserWindow({
    width: 800,
    height: 600,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      preload: path.join(path.dirname(thisFilename), '../dist/main.js'), // Compiled at src/main.ts
    },
  })
  mainWindow.loadFile(path.join(path.dirname(thisFilename), '../src/main.html'))
}
electron.app.whenReady().then(() => {
  createWindow()
  electron.app.on('activate', () => {
    if (electron.BrowserWindow.getAllWindows().length === 0)
      createWindow()
  })
})
electron.app.on('window-all-closed', () => {
  // MacOS doing shenanigans
  if (process.platform !== 'darwin')
    electron.app.quit()
})