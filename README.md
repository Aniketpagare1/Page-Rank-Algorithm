
## 📚 PageRank Algorithm

The **PageRank Algorithm** is a fundamental concept in the field of search engines and web page ranking. Developed by Google founders Larry Page and Sergey Brin, it determines the importance of web pages based on their link structure. This project provides a C implementation of the PageRank algorithm, showcasing how web pages can be ranked according to the likelihood of a user landing on them by following random links.

## 🛠️ Project Structure

- **`page_rank.c`**: The main C source file containing the implementation of the PageRank algorithm.
- **`input.txt`**: Sample input file with web page link data.
- **`output.txt`**: Output file where the PageRank results are written.


## 📥 Input File Format

The input file should follow this structure:

1. The first line contains the number of web pages, `N`.
2. Each subsequent line represents a link from a source page to a destination page, formatted as `source destination`.

**Example (`input.txt`):**
```
3
0 1
1 2
2 0
```

## 🚀 Compilation and Execution

### Compilation

To compile the C source code, use GCC or any compatible C compiler:

```bash
gcc -o pagerank page_rank.c
```

### Execution

Run the compiled program with the input file and desired output file:

```bash
./pagerank input.txt output.txt
```

The program will process the data from `input.txt` and generate the PageRank results in `output.txt`.

## 📈 Output

The `output.txt` file will include:
- The damping factor used in calculations.
- The epsilon threshold for convergence.
- The number of nodes in the graph.
- PageRank values for each page, sorted in descending order.
- The time taken to compute the PageRank.
- The time complexity of the algorithm.

**Example (`output.txt`):**
```
Damping Factor: 0.85
Epsilon: 0.0001
Number of Nodes: 3

Page Rank of Each Page (Descending Order):
Page 2: Page Rank = 0.5000    Out Degree = 1
Page 1: Page Rank = 0.3333    Out Degree = 1
Page 0: Page Rank = 0.1667    Out Degree = 1

Start Time: HH:MM:SS
End Time: HH:MM:SS
Time Taken: X.XXXX seconds

Time Complexity: O(n^2)
```


## 🙌 Acknowledgements

- The PageRank algorithm was originally developed by Larry Page and Sergey Brin.
- This implementation is adapted for educational purposes.

This version of the `README.md` file features clear headings, bullet points, and examples to make it user-friendly and visually appealing.
