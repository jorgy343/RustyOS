#!/bin/sh

cd ../../Output/Doxygen/
rm -r html
rm -r latex

doxygen ../../Scripts/Common/Doxygen.config