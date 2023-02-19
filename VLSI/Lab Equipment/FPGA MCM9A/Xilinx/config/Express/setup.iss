[InstallShield Silent]
Version=v3.00.000
File=Response File

[Application]
Name=FPGA Express
Version=3.1.1000
Company=Synopsys

[DlgOrder]
Dlg0=SdWelcome-0
Count=6
Dlg1=SdRegisterUser-0
Dlg2=SdConfirmRegistration-0
Dlg3=AskPath-0
Dlg4=SdSelectFolder-0
Dlg5=SdStartCopy-0

[SdWelcome-0]
Result=1

[SdRegisterUser-0]
szName=USERNAME
szCompany=COMPANY_NAME
Result=1

[SdConfirmRegistration-0]
Result=1

[AskPath-0]
szPath=C:\Synopsys\FPGA_Express\
Result=1

[SdSelectFolder-0]
szFolder=Synopsys
Result=1

[SdStartCopy-0]
Result=1
