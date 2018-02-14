while read -r line < /dev/ttyAMA0; do
  echo -ne $line > /dev/hidg0
  echo $result > /dev/ttyAMA0
done
