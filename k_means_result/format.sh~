#!/bin/bash

for r in `find -name "*_result.txt" | sort`; do
    grep "Average" $r | awk '{print $3}'
done

