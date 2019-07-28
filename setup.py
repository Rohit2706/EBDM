import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name = "EBDM",
    version = "1.0.0",
    author = "Rohit Jain",
    author_email = "rohitjain2706@gmail.com",
    description = "Entropy Based Distance Metric",
    long_description = long_description,
    long_description_content_type = "text/markdown",
    url = "https://github.com/Rohit2706/EBDM",
    packages = setuptools.find_packages(),
    keywords = "entropy questionnnaire distance",
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
