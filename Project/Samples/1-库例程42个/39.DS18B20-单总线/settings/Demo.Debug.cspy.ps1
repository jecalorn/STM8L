param([String]$debugfile = "");

# This powershell file has been generated by the IAR Embedded Workbench
# C - SPY Debugger, as an aid to preparing a command line for running
# the cspybat command line utility using the appropriate settings.
#
# Note that this file is generated every time a new debug session
# is initialized, so you may want to move or rename the file before
# making changes.
#
# You can launch cspybat by typing Powershell.exe -File followed by the name of this batch file, followed
# by the name of the debug file (usually an ELF / DWARF or UBROF file).
#
# Read about available command line parameters in the C - SPY Debugging
# Guide. Hints about additional command line parameters that may be
# useful in specific cases :
#   --download_only   Downloads a code image without starting a debug
#                     session afterwards.
#   --silent          Omits the sign - on message.
#   --timeout         Limits the maximum allowed execution time.
#


if ($debugfile -eq "")
{
& "D:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\common\bin\cspybat" -f "D:\淘宝开发资料\STM8L152-蓝旗嵌入式\例程\IAR例程\STM8L152例程222\STM8L152例程\1-库例程42个-不断更新，客观评价享永久下载最新版权\39.DS18B20-单总线\settings\Demo.Debug.general.xcl" --backend -f "D:\淘宝开发资料\STM8L152-蓝旗嵌入式\例程\IAR例程\STM8L152例程222\STM8L152例程\1-库例程42个-不断更新，客观评价享永久下载最新版权\39.DS18B20-单总线\settings\Demo.Debug.driver.xcl" 
}
else
{
& "D:\Program Files (x86)\IAR Systems\Embedded Workbench 8.0\common\bin\cspybat" -f "D:\淘宝开发资料\STM8L152-蓝旗嵌入式\例程\IAR例程\STM8L152例程222\STM8L152例程\1-库例程42个-不断更新，客观评价享永久下载最新版权\39.DS18B20-单总线\settings\Demo.Debug.general.xcl" --debug_file=$debugfile --backend -f "D:\淘宝开发资料\STM8L152-蓝旗嵌入式\例程\IAR例程\STM8L152例程222\STM8L152例程\1-库例程42个-不断更新，客观评价享永久下载最新版权\39.DS18B20-单总线\settings\Demo.Debug.driver.xcl" 
}
