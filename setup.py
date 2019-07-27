import setuptools

with open("README.md", "r") as fh:
    long_description = fh.read()

setuptools.setup(
    name="EBDM-Rohit2706",
    version="0.0.1",
    author="Rohit Jain",
    author_email="rohitjain2706@gmail.com",
    description="Entropy Based Distance Metric",
    long_description=long_description,
    long_description_content_type="text/markdown",
    url="https://github.com/rohitjain2706/EBDM",
    packages=setuptools.find_packages(),
    classifiers=[
        "Programming Language :: Python :: 3",
        "License :: OSI Approved :: MIT License",
        "Operating System :: OS Independent",
    ],
)
