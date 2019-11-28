#!/bin/bash

IDL_NAME=$1
rpcgen -C -a $IDL_NAME
mv Makefile.calculator Makefile