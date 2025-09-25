#!/bin/bash
head -n 1 $1 > $2 ; tail -n +3 $1 >> $2
