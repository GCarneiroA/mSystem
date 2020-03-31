# ***********************************************************
#
# DevOS 2012
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF
# ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED
# TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
# PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT
# SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
# FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
# AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR
# THE USE OR OTHER DEALINGS IN THE SOFTWARE.
# 
# ***********************************************************
# ***********************************************************

.code16
.intel_syntax noprefix
.text
.org 0x0

LOAD_SEGMENT = 0x2000
FAT_SEGMENT  = 0x0ee0

.global main
main:
	jmp short start
	nop

# INCLUDES
.include "bootsector.s"
.include "functions.s"
.include "macros.s"
.include "a20.s"
.include "descriptors.s"

# PROGRAM DATA
filename:		.asciz "KERNEL  BIN"
rebootmsg:    	.asciz "Press any key to reboot.\r\n"
diskerror:    	.asciz "Disk error. "
a20error:		.asciz "A20 unavailable. "
root_strt:   	.byte 0,0      # hold offset of root directory on disk
root_scts:   	.byte 0,0      # holds # sectors in root directory
file_strt:   	.byte 0,0      # holds offset of bootloader on disk
msg:          	.asciz "Second stage bootloader...\r\n"

idt:
	.word		2048
	.int		0x0

gdt:
	.word		24
	.int		2048

# 
# Booting has failed because of a disk error. 
# Inform the user and reboot.
# 
bootFailure:
    mWriteString diskerror
    mReboot

start:
	mWriteString msg
	mCopyBootSector
	mFindFile filename, LOAD_SEGMENT
	mReadFile LOAD_SEGMENT, FAT_SEGMENT
	mResetDiskSystem
	mEnableA20
	mSetupIDT
	mSetupGDT
	mLoadDescriptorTables
	mGoProtected
	mClearPrefetchQueue
	mSetup386Segments
	mJumpToKernel



# .fill 1024, 1, 1              # Pad 1K with 1-bytes to test file larger than 1 sector
