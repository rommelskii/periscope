# Periscope

A C-based client-server networking and logging utility.

## Project Structure

```text
periscope/
├── CMakeLists.txt         # Top-level build configuration
├── build.sh               # Build automation script
├── run_tests.sh           # Test execution script
├── include/               # Header files
│   ├── file_utils.h       # File I/O utilities
│   ├── log.h              # Logging interface
│   ├── log_serialize.h    # Data serialization logic
│   └── server_utils.h     # Networking/socket helpers
├── src/                   # Source files
│   ├── CMakeLists.txt
│   ├── file_utils.c
│   ├── log.c
│   ├── log_serialize.c
│   ├── psc_client.c       # Client implementation
│   ├── psc_server.c       # Server implementation
│   └── server_utils.c
├── tests/                 # Test suite
│   ├── CMakeLists.txt
│   ├── include/
│   │   └── testing_utils.h
│   ├── test_log.c
│   ├── test_log_fmt.c
│   ├── test_log_serialize.c
│   └── test_server.c
└── lib/                   # Compiled static libraries
    └── libperiscope_core.a
