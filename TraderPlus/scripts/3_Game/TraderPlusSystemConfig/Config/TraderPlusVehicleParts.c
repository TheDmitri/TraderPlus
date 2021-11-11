class TraderPlusVehicleParts
{
  string VehicleName;
  int    Height;
  ref TStringArray VehicleParts;

  void TraderPlusVehicleParts(string name)
  {
    VehicleName = name;
    VehicleParts = new TStringArray;
  }

  void AddAttachmentsToVehicle(string partname)
  {
    VehicleParts.Insert(partname);
  }
}
