# Changelog for TsVitch v0.1.0

## [0.1.0] - Initial Release

### Features
- **Multimedia Streaming**: Stream IPTV channels directly on your Nintendo Switch with support for M3U playlists.
- **Optimized UI**: User interface designed for the Nintendo Switch touchscreen and Joy-Con controls.
- **Default Playlist**: Includes a preloaded playlist sourced from the [Free-TV/IPTV repository](https://github.com/Free-TV/IPTV).
- **Multilanguage Support**: Offers multiple audio tracks, subtitles, and language options.
- **Cross-Platform Development**: 
  - Supports Nintendo Switch as the primary target platform.
  - macOS support for desktop testing and builds.
- **Docker Support**: Streamlined cross-compilation environment using Docker for building the Switch executable (`tsvitch.nro`).
- **Custom Dependencies**: Incorporates advanced features through tailored libraries like ffmpeg, libmpv, and wiliwili.

### Technical Additions
- **Build Methods**:
  - Native build environment with DevkitPro for Switch compatibility.
  - Desktop builds supported via CMake and Homebrew on macOS.
- **Utilities**:
  - Option to install a desktop shortcut for streamlined app launching on the Switch.
  - OpenGL build support.
- **Acknowledgements**:
  - Integrated contributions from open-source projects like Borealis (UI), FFmpeg (video processing), and multiple libraries for JSON handling, QR code generation, and SVG rendering.

### Disclaimers
- **Legal Compliance**: The app does not host or provide IPTV content. Users must ensure their playlists comply with local laws.
- **Educational Purpose**: Provided "as-is" without warranties. The author disclaims responsibility for misuse or damages.

---

This release lays the foundation for turning your Nintendo Switch into a multimedia powerhouse! 🚀
