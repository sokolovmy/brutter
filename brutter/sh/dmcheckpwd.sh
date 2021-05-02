#!/bin/sh

ldapsearch -x -D "cn=directory manager" -w $1 -s base -b "" "objectclass=*" -h 10.214.99.124