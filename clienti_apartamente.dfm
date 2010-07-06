object frmClientiAp: TfrmClientiAp
  Left = 0
  Top = 0
  BorderStyle = bsSingle
  Caption = 'Adauga client apartamente'
  ClientHeight = 393
  ClientWidth = 647
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
  object Label7: TLabel
    Left = 546
    Top = 211
    Width = 88
    Height = 13
    Alignment = taCenter
    Caption = 'Ultima modificare: '
  end
  object Label8: TLabel
    Left = 546
    Top = 230
    Width = 88
    Height = 13
    Alignment = taCenter
    AutoSize = False
    Caption = 'Label8'
  end
  object GroupBox3: TGroupBox
    Left = 3
    Top = 211
    Width = 305
    Height = 180
    Caption = 'Informatii proprietar'
    TabOrder = 0
    object Label3: TLabel
      Left = 8
      Top = 84
      Width = 46
      Height = 13
      Caption = 'Informatii'
    end
    object txtNume: TLabeledEdit
      Left = 8
      Top = 28
      Width = 289
      Height = 21
      EditLabel.Width = 27
      EditLabel.Height = 13
      EditLabel.Caption = 'Nume'
      MaxLength = 255
      TabOrder = 0
    end
    object memInfo: TMemo
      Left = 8
      Top = 99
      Width = 289
      Height = 76
      MaxLength = 255
      TabOrder = 1
    end
    object txtTel: TLabeledEdit
      Left = 8
      Top = 64
      Width = 289
      Height = 21
      EditLabel.Width = 36
      EditLabel.Height = 13
      EditLabel.Caption = 'Telefon'
      MaxLength = 255
      TabOrder = 2
    end
  end
  object GroupBox2: TGroupBox
    Left = 416
    Top = 211
    Width = 119
    Height = 180
    Caption = 'Imbunatatiri'
    TabOrder = 1
    object cblImbunatatiri: TCheckListBox
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 109
      Height = 157
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
        'Repartitoare'
        'Boiler'
        'Contor gaz')
      ParentColor = True
      TabOrder = 0
    end
  end
  object GroupBox1: TGroupBox
    Left = 3
    Top = 4
    Width = 641
    Height = 201
    Caption = 'Informatii apartament'
    TabOrder = 2
    object Label4: TLabel
      Left = 210
      Top = 87
      Width = 38
      Height = 13
      Caption = 'Moneda'
    end
    object Label5: TLabel
      Left = 98
      Top = 123
      Width = 60
      Height = 13
      Caption = 'Decomandat'
    end
    object Label10: TLabel
      Left = 8
      Top = 14
      Width = 27
      Height = 13
      Caption = 'Judet'
    end
    object Label11: TLabel
      Left = 8
      Top = 50
      Width = 46
      Height = 13
      Caption = 'Localitate'
    end
    object Label1: TLabel
      Left = 8
      Top = 87
      Width = 84
      Height = 13
      Caption = 'Numar de camere'
    end
    object Label2: TLabel
      Left = 303
      Top = 14
      Width = 73
      Height = 13
      Cursor = crHandPoint
      Hint = 'Adaugati zona'
      Caption = 'Zone preferate'
      ParentShowHint = False
      ShowHint = True
      OnClick = Label2Click
    end
    object Label6: TLabel
      Left = 471
      Top = 14
      Width = 63
      Height = 13
      Cursor = crHandPoint
      Hint = 'Adaugati zona'
      Caption = 'Zone excluse'
      ParentShowHint = False
      ShowHint = True
      OnClick = Label2Click
    end
    object txtPretMin: TLabeledEdit
      Left = 210
      Top = 29
      Width = 87
      Height = 21
      EditLabel.Width = 49
      EditLabel.Height = 13
      EditLabel.Caption = 'Pret minim'
      MaxLength = 10
      TabOrder = 1
      Text = '6'
      OnKeyPress = txtPerContractKeyPress
    end
    object txtMoneda: TComboBox
      Left = 210
      Top = 104
      Width = 87
      Height = 21
      Style = csDropDownList
      TabOrder = 2
      Items.Strings = (
        'RON'
        'EUR'
        'USD')
    end
    object txtDsc: TComboBox
      Left = 98
      Top = 137
      Width = 199
      Height = 21
      Style = csDropDownList
      TabOrder = 3
      Items.Strings = (
        'Decomandat'
        'Semidecomandat'
        'Nedecomandat'
        'Circular')
    end
    object txtJudet: TComboBox
      Left = 8
      Top = 29
      Width = 196
      Height = 21
      Style = csDropDownList
      DropDownCount = 20
      TabOrder = 0
      OnChange = txtJudetChange
    end
    object txtLocalitate: TComboBox
      Left = 8
      Top = 65
      Width = 171
      Height = 21
      Style = csDropDownList
      DropDownCount = 20
      TabOrder = 4
      OnChange = txtLocalitateChange
    end
    object btnLocalitate: TButton
      Left = 183
      Top = 65
      Width = 21
      Height = 21
      Caption = '+'
      TabOrder = 5
      OnClick = btnLocalitateClick
    end
    object txtZonePreferate: TListBox
      Left = 303
      Top = 29
      Width = 162
      Height = 164
      ExtendedSelect = False
      ItemHeight = 13
      Items.Strings = (
        '1'
        '2'
        '3'
        '34'
        '5'
        '5'
        '6'
        '7'
        '8')
      MultiSelect = True
      TabOrder = 6
    end
    object txtNrcam: TListBox
      Left = 8
      Top = 104
      Width = 84
      Height = 89
      ExtendedSelect = False
      ItemHeight = 13
      Items.Strings = (
        'Garsoniera'
        '1'
        '2'
        '3'
        '4'
        '5')
      MultiSelect = True
      TabOrder = 7
    end
    object txtNrPersoane: TLabeledEdit
      Left = 98
      Top = 104
      Width = 106
      Height = 21
      EditLabel.Width = 79
      EditLabel.Height = 13
      EditLabel.Caption = 'Numar persoane'
      MaxLength = 50
      TabOrder = 8
      Text = '6'
    end
    object txtPretMax: TLabeledEdit
      Left = 210
      Top = 65
      Width = 87
      Height = 21
      EditLabel.Width = 53
      EditLabel.Height = 13
      EditLabel.Caption = 'Pret maxim'
      MaxLength = 10
      TabOrder = 9
      Text = '6'
      OnKeyPress = txtPerContractKeyPress
    end
    object txtZoneExcluse: TListBox
      Left = 471
      Top = 29
      Width = 162
      Height = 164
      ExtendedSelect = False
      ItemHeight = 13
      Items.Strings = (
        '1'
        '2'
        '3'
        '34'
        '5'
        '5'
        '6'
        '7'
        '8')
      MultiSelect = True
      TabOrder = 10
    end
    object txtPerContract: TLabeledEdit
      Left = 98
      Top = 172
      Width = 199
      Height = 21
      EditLabel.Width = 160
      EditLabel.Height = 13
      EditLabel.Caption = 'Perioada contract (numar de luni)'
      MaxLength = 4
      TabOrder = 11
      Text = '6'
      OnKeyPress = txtPerContractKeyPress
    end
  end
  object GroupBox4: TGroupBox
    Left = 309
    Top = 211
    Width = 106
    Height = 90
    Caption = 'Mobilat'
    TabOrder = 3
    object cblMobilat: TCheckListBox
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 96
      Height = 67
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      DoubleBuffered = False
      ItemHeight = 20
      Items.Strings = (
        'Mobilat'
        'Semimobilat'
        'Nemobilat')
      ParentColor = True
      ParentDoubleBuffered = False
      Style = lbOwnerDrawFixed
      TabOrder = 0
    end
  end
  object GroupBox5: TGroupBox
    Left = 309
    Top = 301
    Width = 106
    Height = 90
    Caption = 'Utilat'
    TabOrder = 4
    object cblUtilat: TCheckListBox
      AlignWithMargins = True
      Left = 5
      Top = 18
      Width = 96
      Height = 67
      Align = alClient
      BevelInner = bvNone
      BevelOuter = bvNone
      BorderStyle = bsNone
      DoubleBuffered = False
      ItemHeight = 20
      Items.Strings = (
        'Utilat'
        'Semiutilat'
        'Neutilat')
      ParentColor = True
      ParentDoubleBuffered = False
      Style = lbOwnerDrawFixed
      TabOrder = 0
    end
  end
  object btnStergeTot: TButton
    Left = 551
    Top = 298
    Width = 75
    Height = 25
    Caption = 'S&terge tot'
    TabOrder = 5
    OnClick = btnStergeTotClick
  end
  object btnInchiriat: TButton
    Left = 551
    Top = 267
    Width = 75
    Height = 25
    Caption = 'A inchiriat'
    TabOrder = 6
    OnClick = btnInchiriatClick
  end
  object btnSalveaza: TButton
    Left = 551
    Top = 360
    Width = 75
    Height = 25
    Caption = '&Salveaza'
    Default = True
    TabOrder = 7
    OnClick = btnSalveazaClick
  end
  object btnRenunta: TButton
    Left = 551
    Top = 329
    Width = 75
    Height = 25
    Cancel = True
    Caption = '&Renunta'
    TabOrder = 8
    OnClick = btnRenuntaClick
  end
  object insertQuery: TUpdateSQL
    Left = 264
    Top = 320
  end
  object SQL: TUpdateSQL
    Left = 216
    Top = 320
  end
  object getLocId: TQuery
    Left = 176
    Top = 320
  end
end
