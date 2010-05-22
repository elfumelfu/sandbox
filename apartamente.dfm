object frmAp: TfrmAp
  Left = 0
  Top = 0
  Caption = 'frmAp'
  ClientHeight = 432
  ClientWidth = 543
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poMainFormCenter
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object RadioGroup1: TRadioGroup
    Left = 432
    Top = 159
    Width = 106
    Height = 90
    Caption = 'Mobilat'
    ItemIndex = 2
    Items.Strings = (
      'Mobilat'
      'Semimobilat'
      'Nemobilat')
    TabOrder = 3
  end
  object btnSalveaza: TButton
    Left = 463
    Top = 255
    Width = 75
    Height = 25
    Caption = '&Salveaza'
    Default = True
    TabOrder = 0
    OnClick = btnSalveazaClick
  end
  object GroupBox1: TGroupBox
    Left = 8
    Top = 8
    Width = 424
    Height = 241
    Caption = 'Informatii apartament'
    TabOrder = 1
    object Label1: TLabel
      Left = 8
      Top = 99
      Width = 27
      Height = 13
      Caption = 'Altele'
    end
    object Label2: TLabel
      Left = 325
      Top = 56
      Width = 64
      Height = 13
      Caption = 'Data expirarii'
    end
    object txtNrcam: TLabeledEdit
      Left = 8
      Top = 32
      Width = 73
      Height = 21
      EditLabel.Width = 69
      EditLabel.Height = 13
      EditLabel.Caption = 'Numar camere'
      TabOrder = 0
      Text = '1'
    end
    object txtZona: TLabeledEdit
      Left = 87
      Top = 32
      Width = 93
      Height = 21
      EditLabel.Width = 24
      EditLabel.Height = 13
      EditLabel.Caption = 'Zona'
      TabOrder = 1
      Text = '2'
    end
    object txtBloc: TLabeledEdit
      Left = 186
      Top = 32
      Width = 73
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = 'Bloc'
      TabOrder = 2
      Text = '3'
    end
    object txtAp: TLabeledEdit
      Left = 265
      Top = 32
      Width = 73
      Height = 21
      EditLabel.Width = 57
      EditLabel.Height = 13
      EditLabel.Caption = 'Apartament'
      TabOrder = 3
      Text = '4'
    end
    object txtEtaj: TLabeledEdit
      Left = 344
      Top = 32
      Width = 73
      Height = 21
      EditLabel.Width = 19
      EditLabel.Height = 13
      EditLabel.Caption = 'Etaj'
      TabOrder = 4
      Text = '5'
    end
    object txtDsc: TLabeledEdit
      Left = 245
      Top = 72
      Width = 73
      Height = 21
      EditLabel.Width = 60
      EditLabel.Height = 13
      EditLabel.Caption = 'Decomandat'
      TabOrder = 5
      Text = '9'
    end
    object txtGs: TLabeledEdit
      Left = 166
      Top = 72
      Width = 73
      Height = 21
      EditLabel.Width = 59
      EditLabel.Height = 13
      EditLabel.Caption = 'Grup sanitar'
      TabOrder = 6
      Text = '8'
    end
    object txtMoneda: TLabeledEdit
      Left = 87
      Top = 72
      Width = 73
      Height = 21
      EditLabel.Width = 38
      EditLabel.Height = 13
      EditLabel.Caption = 'Moneda'
      TabOrder = 7
      Text = '7'
    end
    object txtPret: TLabeledEdit
      Left = 8
      Top = 72
      Width = 73
      Height = 21
      EditLabel.Width = 20
      EditLabel.Height = 13
      EditLabel.Caption = 'Pret'
      TabOrder = 8
      Text = '6'
    end
    object memAltele: TMemo
      Left = 8
      Top = 118
      Width = 409
      Height = 117
      Lines.Strings = (
        '21'
        '34'
        '54')
      TabOrder = 9
    end
  end
  object GroupBox2: TGroupBox
    Left = 432
    Top = 8
    Width = 106
    Height = 153
    Caption = 'Imbunatatiri'
    TabOrder = 2
    object CheckListBox1: TCheckListBox
      Left = 2
      Top = 15
      Width = 102
      Height = 136
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      ItemHeight = 13
      Items.Strings = (
        'Balcon'
        'Gresie'
        'Faianta'
        'Termopan'
        'Parchet'
        'Usa metalica'
        'Centrala termica'
        'Aer conditionat'
        'Apometre'
        'Repartitoare')
      ParentColor = True
      TabOrder = 0
    end
  end
  object txtDataExpirarii: TDateTimePicker
    Left = 332
    Top = 80
    Width = 93
    Height = 21
    Date = 40284.850948078700000000
    Time = 40284.850948078700000000
    TabOrder = 4
  end
  object GroupBox3: TGroupBox
    Left = 8
    Top = 255
    Width = 377
    Height = 174
    Caption = 'Informatii proprietar'
    TabOrder = 5
    object Label3: TLabel
      Left = 8
      Top = 55
      Width = 46
      Height = 13
      Caption = 'Informatii'
    end
    object txtNume: TLabeledEdit
      Left = 8
      Top = 32
      Width = 194
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Nume'
      TabOrder = 0
    end
    object memInfo: TMemo
      Left = 8
      Top = 72
      Width = 361
      Height = 94
      TabOrder = 1
    end
    object txtTel: TLabeledEdit
      Left = 208
      Top = 32
      Width = 160
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = 'Telefon'
      TabOrder = 2
    end
  end
  object btnStergeTot: TButton
    Left = 463
    Top = 286
    Width = 75
    Height = 25
    Caption = 'S&terge tot'
    TabOrder = 6
    OnClick = btnStergeTotClick
  end
  object btnRenunta: TButton
    Left = 463
    Top = 317
    Width = 75
    Height = 25
    Caption = '&Renunta'
    TabOrder = 7
    OnClick = btnRenuntaClick
  end
  object SQL: TUpdateSQL
    Left = 392
    Top = 256
  end
end
