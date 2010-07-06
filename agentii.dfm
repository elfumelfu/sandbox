object frmAgentii: TfrmAgentii
  Left = 0
  Top = 0
  Caption = 'Agentii'
  ClientHeight = 120
  ClientWidth = 253
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object txtNume: TLabeledEdit
    Left = 8
    Top = 24
    Width = 237
    Height = 21
    EditLabel.Width = 27
    EditLabel.Height = 13
    EditLabel.Caption = 'Nume'
    TabOrder = 0
  end
  object txtTelefon: TLabeledEdit
    Left = 8
    Top = 64
    Width = 237
    Height = 21
    EditLabel.Width = 36
    EditLabel.Height = 13
    EditLabel.Caption = 'Telefon'
    TabOrder = 1
  end
  object btnSalveaza: TButton
    Left = 170
    Top = 91
    Width = 75
    Height = 25
    Caption = '&Salveaza'
    Default = True
    TabOrder = 2
    OnClick = btnSalveazaClick
  end
  object btnStergeTot: TButton
    Left = 89
    Top = 91
    Width = 75
    Height = 25
    Caption = 'S&terge tot'
    TabOrder = 3
    OnClick = btnStergeTotClick
  end
  object btnRenunta: TButton
    Left = 8
    Top = 91
    Width = 75
    Height = 25
    Caption = '&Renunta'
    TabOrder = 4
    OnClick = btnRenuntaClick
  end
  object SQL: TUpdateSQL
    Left = 392
    Top = 256
  end
end
