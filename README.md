# SPLAY - PREFIX CODES
This C project implements Huffman coding, a popular algorithm for lossless data compression. Huffman coding assigns variable-length codes to input characters based on their frequencies, with more frequent characters receiving shorter codes, optimizing overall data compression. The project also integrates splaying techniques to dynamically adjust the Huffman tree structure during encoding, potentially improving efficiency by prioritizing frequently accessed nodes.

# Key components include:
- **Data Structures**: Uses `struct node` for Huffman tree nodes and `struct MinHeap` for managing a min heap.
- **Functions**: Includes functions for heap operations (`create`, `insertMinHeap`, `buildMinHeap`), tree construction (`buildTree`), and encoding (`printCodes`, `encode`), alongside splaying operations (`semisplayright`, `semisplayleft`, `splay`, `semisplaying`).
- **Utility Functions**: Supports character frequency initialization (`freqinit`), duplicate removal (`removeDuplicate`), and checks (`checkchar`, `checkInArr`).

Overall, this project illustrates how Huffman coding can be enhanced with splaying to optimize encoding efficiency, crucial in applications requiring efficient data compression and retrieval.
