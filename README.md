# Latecall
> Latecall do things in future, meanwhile it remains dormant in your system and survives crash and reboot. Latecall is coded in c++ which makes it lightweight.

## Installation and usage

Linux:

```sh
git clone https://github.com/humblewolf/latecall
cd latecall
make all
sudo make install
<change config file at /usr/local/etc/latecall.ini as per your prefrences>
sudo systemctl start latecall
```

## Config file

> Location : /usr/local/etc/latecall.ini

gap - gap between pre and main script execution (in hours)
time - time to execute main script (in hours)
preScript - shell script to execute {gap} hours before main shell script execution
script - main shell script to execute after {time} hours

## Meta

humblewolf –  humblewolff@gmail.com

## Contributing

1. Fork it (<https://github.com/humblewolf/latecall/fork>)
2. Create your feature branch (`git checkout -b feature/fooBar`)
3. Commit your changes (`git commit -am 'Add some fooBar'`)
4. Push to the branch (`git push origin feature/fooBar`)
5. Create a new Pull Request
