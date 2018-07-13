#!/bin/bash

cur_dir=$(cd $(dirname $0);pwd)

append_text=$(cat << EOS


include_directories("lib/MSAHParser.git/src")
EOS
)

echo $append_text >> $cur_dir/CMakeListsPrivate.txt
