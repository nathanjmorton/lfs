# Useful Sysadmin Scripts

## find a file and list all its locations
```sh
count=0; find / -type f -iname "chroot" 2>/dev/null | while read -r line; do ((count++)); echo "Location $count: $line"; done; echo -e "\nSummary: Found $count matching directory/directories."
```
- count=0; sets a loop counter
- find / -type f -iname "chroot" finds from / any file with case insensitive name chroot
- 2>/dev/null supresses errors and does not print to stdout (current terminal session log)
- | while read -r line; pipes the find operation to a loop (while) that reads (read) a raw (-r) line of text from the input stream and assigns it to a variable (line)
- do ((count++)); ((..)) bash arithmetic to increment count
- echo "Location $count: $line"; done; interpolate the count and line variable once data is found 
- echo -e "\nSummary: Found $count matching directories." -e is an escape flag to treat backslash as an escape character and in this case it is used with \n to print Summary on a newline.
