# EBDM 

[![PyPI version fury.io](https://badge.fury.io/py/ansicolortags.svg)](https://pypi.python.org/pypi/ansicolortags/)

Python package for finding Entropy-Based Distance Metric. An implementation of the following paper:

Y. Zhang, Y. Cheung and K. C. Tan, "[A Unified Entropy-Based Distance Metric for Ordinal-and-Nominal-Attribute Data Clustering](http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8671525&isnumber=8949827)," in IEEE Transactions on Neural Networks and Learning Systems, vol. 31, no. 1, pp. 39-52, Jan. 2020.
doi: 10.1109/TNNLS.2019.2899381

## Getting Started

### Prerequisites

Note EBDM requires Python 3.x

These instructions will get you a copy of the package up and running on your local machine for development and testing purposes.

Before getting started, make sure that you have the following libraries already installed:

```
import pandas as pd
import math
```
### Installing

In your source file, import the library and start using the functions step-by-step as mentioned in the below section

```
import EBDM as ebd
```
For accessing modules, use
```
ebd.<module_name>
```

For reading the data, make sure that you’ve separated ordinal and nominal into separate CSV files.

Usage
```
nominal_features_dict = ebd.read_nom('nominal_data.csv')
ordinal_features_dict = ebd.read_ord('ordinal_data.csv')
```

## Contributing

Feel free to make contributions to this repository by submitting well-documented pull requests and raising issues.

### Documentation

To run the documentation website, open <code>docs/_build/html/index.html</code>

*If you're making changes to the source code of docs folder, make sure that you compile a clean build in the shell using*
<code>make clean; make html</code>

## Authors

* **Rohit Jain**  - [Rohit2706](https://github.com/Rohit2706)
* **Ishita Mediratta**  - [ishitamed19](https://github.com/ishitamed19)
* **Ahsan Abbas** - [ahsanabbas123](https://github.com/ahsanabbas123)

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Sincere thanks to Dr. Mitali Mukerjee, Dr. Bhavana Prasher, Mr. Rintu Kutum and the AyurGenomics Group for guiding us throughout our internship period at the CSIR-IGIB, New Delhi.



