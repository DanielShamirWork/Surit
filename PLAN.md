# Project Roadmap: Surit
**Goal:** C++ Huffman Compression Library & CLI  
**Timeline:** 6 Weeks  
**Deadline:** [Insert Date]

---

### Weeks 1-2: Core Compression Logic (The "Engine")
**Focus:** Transforming raw data into Huffman codes.

- [V] **Frequency Analysis:** Implement a function to read input bytes and count character occurrences.
- [V] **Priority Queue:** Create a min-heap structure to sort characters by frequency.
- [V] **Construct Huffman Tree:** Build the binary tree where leaves are characters and nodes are combined frequencies.
- [V] **Generate Lookup Table:** Traverse the tree to create a map of bit-codes (e.g., `'A' -> 010`).
- [ ] **Implement "BitWriter" Class:**
    * *Challenge:* Standard C++ I/O writes bytes (8 bits).
    * *Task:* Create a class that buffers individual bits and flushes them to a stream only when a full byte is ready.

### Week 3: File I/O & Decompression (The CLI)
**Focus:** Making the library usable on actual files.

- [ ] **Define File Header Format:**
    * Design a schema to store the Frequency Table (or serialized Tree) at the start of the file so the decoder knows how to interpret the bits.
- [ ] **Implement "BitReader" Class:** The inverse of BitWriter (reads byte, serves bits).
- [ ] **Implement Decompression Logic:**
    * Read header $\to$ Reconstruct Tree $\to$ Traverse Tree using bits to find characters.
- [ ] **Build Basic CLI:**
    * Parse arguments: `surit -c <file>` (compress) and `surit -d <file>` (decompress).

### Week 4: Thorough Testing Suite (Quality Assurance)
**Focus:** Ensuring data integrity (Lossless means ZERO errors).

- [ ] **Unit Tests:**
    * Test individual components (e.g., does the Priority Queue sort correctly? Does BitWriter handle leftover bits?).
- [ ] **Integration Script:**
    * Write a shell script that automates:
      1. Compress file `A` $\to$ `A.surt`
      2. Decompress `A.surt` $\to$ `A_restored`
      3. Run `diff A A_restored` to check for binary identity.
- [ ] **Edge Case Testing:**
    * Test with: Empty files, files with 1 repeating character (e.g., "aaaaa"), binary files (images), and large text files.

### Week 5: Optimization & Memory Management
**Focus:** Efficiency and C++ Best Practices.

- [ ] **Memory Leak Check:**
    * Run with **Valgrind** to ensure all tree nodes and buffers are freed correctly.
- [ ] **Header Optimization:**
    * Refine the metadata storage to reduce overhead size.
- [ ] **Speed Profiling:**
    * Identify bottlenecks (e.g., string concatenation vs. buffers) and refactor.

### Week 6: Final Polish & Buffer
**Focus:** Documentation and Submission Prep.

- [ ] **Code Cleanup:** Add comments explaining the *Why*, not just the *How*.
- [ ] **Final Manual Reviews:** Try to break the CLI with bad inputs (e.g., non-existent files).
- [ ] **Documentation:** Complete the README and usage guide.
- [ ] **Buffer Time:** Reserved for fixing any stubborn bugs found in Week 4 or 5.
