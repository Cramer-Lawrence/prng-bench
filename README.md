
# 🧪 `quant-prng-bench`
**A performance and distribution benchmark suite for C++ PRNG algorithms**  
Author: [Your Name] — Part of $500K+ Quant Dev Roadmap (Week 2)

---

## 🚀 Overview

`quant-prng-bench` is a C++ benchmarking suite designed to evaluate both **performance** and **distribution quality** across various pseudo-random number generator (PRNG) algorithms under different threading models. It's engineered with **thread-local vs shared vs single-threaded** configurations to showcase real-world performance differences, particularly in multithreaded Quant Dev contexts.

**PRNGs Benchmarked:**
- Linear Congruential Generator (LCG)
- Mersenne Twister (MT19937)
- PCG32
- SplitMix64
- XOR Shift

Each is tested across a configurable range of iteration sizes and thread counts, then profiled for:
- Execution time
- Distribution deviation (average + max deviation from uniformity)

---

## 📊 Sample Results (Charts)

### Time vs Iterations (All PRNGs - Threading Models)
![Time All](./charts/Time-vs-Iterations-All.svg)

### Average Deviation % vs Iterations (All PRNGs)
![Deviation All](./charts/Avg-Deviation-All.svg)

### PRNG-Specific Time Charts:
- [LCG](./charts/Time-vs-Iterations-LCG.svg)
- [MT19937](./charts/Time-vs-Iterations-MT19937.svg)
- [PCG32](./charts/Time-vs-Iterations-PCG32.svg)
- [SplitMix64](./charts/Time-vs-Iterations-Split-Mix-64.svg)
- [XOR Shift](./charts/Time-vs-Iterations-XOR-Shift.svg)

---

## ⚙️ CLI Options

```bash
./prng-bench --low 100000 --high 16000000 --spread 20 --threads 16 --min 0 --max 1000 --file prng-results.csv
```

**Options:**
- `--low`: Min iterations per thread
- `--high`: Max iterations per thread
- `--spread`: Number of total steps
- `--threads`: Number of worker threads
- `--min`: Minimum PRNG output value
- `--max`: Maximum PRNG output value
- `--file`: Output file for CSV results

---

## 📁 Project Structure

```
.
├── include/              # PRNGs, benchmark utils, CLI parser
├── src/                  # Source files (split by PRNG/benchmark/CLI)
├── charts/               # Output graphs (.svg and .png)
├── CMakeLists.txt        # CLI11, benchmark linking
├── prng-bench-results.csv
```

---

## 💡 Key Takeaways

- Thread-local PRNGs are optimal in terms of both speed and distribution.
- Shared PRNGs, while safe (via mutex or atomic wrapping), perform drastically worse.
- Distribution anomalies surfaced during initial runs were likely caused by non-thread-safe sharing.
- Spikes in data were traced to system load interference and resolved by adding `std::this_thread::sleep_for`.

---

## ✅ Skills Demonstrated

- Modern C++: smart pointers, RAII, mutex/thread_local/thread join
- Multithreaded benchmarking + CSV export
- Uniformity measurement of PRNGs
- Use of CLI11 for argument parsing
- GitHub-ready documentation and visualizations

---

## 🧠 Lessons Learned

- Thread safety has serious performance tradeoffs in PRNG scenarios.
- Even simple random algorithms have complex behavior under stress.
- Benchmarking requires clean testing environments to avoid noise.
- Visualizations matter—clear graphs tell a much better story than raw data.
