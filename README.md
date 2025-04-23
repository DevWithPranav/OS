# OS Lab Programs

This repository contains various C programs written for understanding core concepts of Operating Systems. Each file represents a different scheduling algorithm, memory management technique, or synchronization problem.

## Contents

### 🔧 CPU Scheduling Algorithms
- **`fcfs.c`**: First-Come, First-Served scheduling.
- **`sjf.c`**: Shortest Job First scheduling.
- **`roundrobin.c`**: Round Robin scheduling.
- **`proirity.c`** *(Note: may be a typo for `priority.c`)*: Priority scheduling.

### 💽 Disk Scheduling Algorithms
- **`diskfcfs.c`**: Disk scheduling using First-Come, First-Served.
- **`disksstf.c`**: Shortest Seek Time First disk scheduling.
- **`diskscan.c`**: SCAN disk scheduling algorithm.

### 📄 Page Replacement Algorithms
- **`pagefifo.c`**: FIFO (First In First Out) page replacement.
- **`pagelru.c`**: LRU (Least Recently Used) page replacement.
- **`pagelfu.c`**: LFU (Least Frequently Used) page replacement.

### 🧅 Synchronization Problems
- **`phill.c`**: Dining Philosophers problem.
- **`producerconsumer.c`**: Producer-Consumer problem using semaphores.
- **`pipe.c`**: Inter-process communication using anonymous pipes.
- **`sharedmemory.c`**: Shared memory demonstration using `shmget` and `shmat`.

### 💳 Memory Allocation
- **`banker.c`**: Banker's Algorithm for deadlock avoidance.

### Misc
- **`a.exe`**: Executable file (likely compiled output).
  
---

## Usage

You can compile any of the `.c` files using `gcc`:
```bash
gcc filename.c -o output
./output
```

Make sure you have build-essential tools installed:
```bash
sudo apt update && sudo apt install build-essential
```

---

## Notes

- These programs are primarily intended for educational purposes and OS lab practice.
- Contributions and improvements are welcome!

