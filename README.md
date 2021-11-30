# EdgeKiller
EdgeKiller is a simple application that fully replaces Microsoft Edge with the Browser of choice, while also intercepting all the `microsoft-edge:` URIs. It was made as alternative to [EdgeDeflector](https://github.com/da2x/EdgeDeflector) as it doesn't work on Windows 11.

## Features
* Replacing Microsoft Edge with the browser of choice (by using Image File Execution Options)
* Replacing default Windows Search web search engine (Bing) with any other (configured in `config.json`)


## Installation
To install EdgeKiller just download the latest release build and follow the installer instructions.

## Building
You can also build EdgeKiller from source.
### Requirements
* Copy of this repository
* Internet connection (for downloading dependencies)
* CMake
* NSIS (added to PATH)

Once located in the repo root you need to run the following commands.
```sh
cmake -S . -B build
cmake --build build --config Release
makensis installer.nsi
```
Now there should be an `install.exe` file in the directory.

## Configuration
You can configure EdgeKiller using `config.json` file located in the installation directory.
|key|default value|meaning|
|---|---|---|
|`preffered_browser_path`|`chrome.exe`|Path to the preffered browser|
|`preffered_search_engine`|`https://www.google.com/search?q={}`|Search engine URL with the query parameter changed to `{}`|


