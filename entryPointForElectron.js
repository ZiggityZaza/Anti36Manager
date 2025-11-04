// No need to manually have this ts as it has few instructions
import * as electron from 'electron'
import * as path from 'path'
import * as url from 'url'
const createWindow = () => {
  const thisFilename = url.fileURLToPath(import.meta.url)
  const mainWindow = new electron.BrowserWindow({
    width: electron.screen.getPrimaryDisplay().workAreaSize.width - 200,
    height: electron.screen.getPrimaryDisplay().workAreaSize.height - 100,
    webPreferences: {
      nodeIntegration: true,
      contextIsolation: false,
      // preload: path.join(path.dirname(thisFilename), './dist/main.js'), // Compiled in src/
    },
  })
  mainWindow.loadFile(path.join(path.dirname(thisFilename), './src/main.html'))
  mainWindow.webContents.openDevTools() // Load dev tools
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