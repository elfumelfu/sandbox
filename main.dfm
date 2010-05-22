object frmMain: TfrmMain
  Left = 0
  Top = 0
  Caption = 'se-inchiriaza.ro'
  ClientHeight = 468
  ClientWidth = 773
  Color = clBtnFace
  DefaultMonitor = dmMainForm
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OldCreateOrder = False
  Position = poScreenCenter
  PixelsPerInch = 96
  TextHeight = 13
  object StatusBar: TStatusBar
    Left = 0
    Top = 449
    Width = 773
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object TreeView1: TTreeView
    Left = 0
    Top = 0
    Width = 161
    Height = 449
    Align = alLeft
    Indent = 19
    TabOrder = 1
    OnChange = TreeView1Change
    Items.NodeData = {
      0302000000340000000000000000000000FFFFFFFFFFFFFFFF00000000000000
      0000000000010B4100700061007200740061006D0065006E00740065002E0000
      000000000000000000FFFFFFFFFFFFFFFF000000000000000000000000010854
      006500720065006E00750072006900}
  end
  object DBGrid1: TDBGrid
    Left = 161
    Top = 0
    Width = 612
    Height = 449
    Align = alClient
    DataSource = DataSource1
    TabOrder = 2
    TitleFont.Charset = DEFAULT_CHARSET
    TitleFont.Color = clWindowText
    TitleFont.Height = -11
    TitleFont.Name = 'Tahoma'
    TitleFont.Style = []
    OnDblClick = DBGrid1DblClick
  end
  object MainMenu1: TMainMenu
    Left = 88
    Top = 56
    object File1: TMenuItem
      Caption = '&Fisier'
      object Iesier1: TMenuItem
        Caption = '&Iesire'
        OnClick = Iesier1Click
      end
    end
    object Apartamente1: TMenuItem
      Caption = '&Apartamente'
      object Adauga1: TMenuItem
        Caption = 'A&dauga'
        OnClick = Adauga1Click
      end
      object Vizualizeaza1: TMenuItem
        Caption = '&Vizualizeaza'
      end
    end
  end
  object Database: TDatabase
    AliasName = 'baza_data'
    DatabaseName = 'seinchirieaza'
    LoginPrompt = False
    Params.Strings = (
      '=')
    SessionName = 'Default'
    AfterConnect = DatabaseAfterConnect
    Left = 24
    Top = 64
  end
  object DataSource1: TDataSource
    DataSet = Query1
    Left = 168
    Top = 40
  end
  object Query1: TQuery
    DatabaseName = 'TEST'
    SQL.Strings = (
      'SELECT * FROM apartamente')
    Left = 200
    Top = 40
  end
  object sqlSelect: TQuery
    DatabaseName = 'baza_data'
    DataSource = DataSource1
    Left = 200
    Top = 88
  end
end
