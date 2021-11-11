class TraderPlusStates
{
  bool AcceptWorn, AcceptDamaged, AcceptBadlyDamaged;

  void TraderPlusStates(bool aw, bool ad, bool abd)
  {
    AcceptWorn = aw;
    AcceptDamaged = ad;
    AcceptBadlyDamaged = abd;
  }
};
