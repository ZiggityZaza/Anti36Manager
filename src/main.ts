// See the Electron documentation for details on how to use preload scripts:
// https://www.electronjs.org/docs/latest/tutorial/process-model#preload-scripts
import * as fs from 'node:fs';

// Write text in DOM at startup
window.addEventListener('DOMContentLoaded', () => {
    const current_directory = fs.realpathSync(process.cwd());
    const div = document.createElement('div');
    div.textContent = current_directory;
    document.body.appendChild(div);
});