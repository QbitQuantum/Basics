// MOV to / from DRx
_Use_decl_annotations_ static void VmmpHandleDrAccess(
    GuestContext *guest_context) {
  HYPERPLATFORM_PERFORMANCE_MEASURE_THIS_SCOPE();
  const MovDrQualification exit_qualification = {
      UtilVmRead(VmcsField::kExitQualification)};
  const auto register_used =
      VmmpSelectRegister(exit_qualification.fields.gp_register, guest_context);

  // Emulate the instruction
  switch (static_cast<MovDrDirection>(exit_qualification.fields.direction)) {
    case MovDrDirection::kMoveToDr:
      // clang-format off
      switch (exit_qualification.fields.debugl_register) {
        case 0: __writedr(0, *register_used); break;
        case 1: __writedr(1, *register_used); break;
        case 2: __writedr(2, *register_used); break;
        case 3: __writedr(3, *register_used); break;
        case 4: __writedr(4, *register_used); break;
        case 5: __writedr(5, *register_used); break;
        case 6: __writedr(6, *register_used); break;
        case 7: __writedr(7, *register_used); break;
        default: break;
      }
      // clang-format on
      break;
    case MovDrDirection::kMoveFromDr:
      // clang-format off
      switch (exit_qualification.fields.debugl_register) {
        case 0: *register_used = __readdr(0); break;
        case 1: *register_used = __readdr(1); break;
        case 2: *register_used = __readdr(2); break;
        case 3: *register_used = __readdr(3); break;
        case 4: *register_used = __readdr(4); break;
        case 5: *register_used = __readdr(5); break;
        case 6: *register_used = __readdr(6); break;
        case 7: *register_used = __readdr(7); break;
        default: break;
      }
      // clang-format on
      break;
    default:
      HYPERPLATFORM_COMMON_BUG_CHECK(HyperPlatformBugCheck::kUnspecified, 0, 0,
                                     0);
      break;
  }

  VmmpAdjustGuestInstructionPointer(guest_context->ip);
}