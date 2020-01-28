# EBDM 

Python package for finding Entropy-Based Distance Metric. An implementation of the following paper:

Y. Zhang, Y. Cheung and K. C. Tan, "A Unified Entropy-Based Distance Metric for Ordinal-and-Nominal-Attribute Data Clustering," in IEEE Transactions on Neural Networks and Learning Systems, vol. 31, no. 1, pp. 39-52, Jan. 2020.
doi: 10.1109/TNNLS.2019.2899381

## Abstract

Ordinal data are common in many data mining and machine learning tasks. Compared to nominal data, the possible values (also called categories interchangeably) of an ordinal attribute are naturally ordered. Nevertheless, since the data values are not quantitative, the distance between two categories of an ordinal attribute is generally not well defined, which surely has a serious impact on the result of the quantitative analysis if an inappropriate distance metric is utilized. From the practical perspective, ordinal-and-nominal-attribute categorical data, i.e., categorical data associated with a mixture of nominal and ordinal attributes, is common, but the distance metric for such data has yet to be well explored in the literature. In this paper, within the framework of clustering analysis, we therefore first propose an entropy-based distance metric for ordinal attributes, which exploits the underlying order information among categories of an ordinal attribute for the distance measurement. Then, we generalize this distance metric and propose a unified one accordingly, which is applicable to ordinal-and-nominal-attribute categorical data. Compared with the existing metrics proposed for categorical data, the proposed metric is simple to use and nonparametric. More importantly, it reasonably exploits the underlying order information of ordinal attributes and statistical information of nominal attributes for distance measurement. Extensive experiments show that the proposed metric outperforms the existing counterparts on both the real and benchmark data sets.
keywords: {Distance measurement;Clustering algorithms;Task analysis;Data analysis;Benchmark testing;Entropy;Categorical data;clustering algorithms;data analysis;distance metric;entropy;order information;ordinal attribute},
URL: http://ieeexplore.ieee.org/stamp/stamp.jsp?tp=&arnumber=8671525&isnumber=8949827

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

* Sincere thanks to Mr. Rintu Kutum for guiding us throughout our internship period at the CSIR-IGIB, New Delhi.



