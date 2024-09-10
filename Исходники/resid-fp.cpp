static int residfp_init(sound_t *psid, int speed, int cycles_per_sec)
{
    sampling_method method;
    char model_text[100];
    char method_text[100];
    float  passband;
    int filters_enabled, model, sampling, passband_percentage;

    if (resources_get_int("SidFilters", &filters_enabled) < 0)
        return 0;

    if (resources_get_int("SidModel", &model) < 0)
        return 0;

    if (resources_get_int("SidResidSampling", &sampling) < 0)
        return 0;

    if (resources_get_int("SidResidPassband", &passband_percentage) < 0)
        return 0;

    passband = speed * passband_percentage / 200.f;
 
    /* Some mostly-common settings for all modes abstracted here. */
    psid->sid->input(0);

    /* Model numbers 8-15 are reserved for distorted 6581s. */
    if (model < 8 || model > 15) {
      psid->sid->set_chip_model(MOS8580FP);
      psid->sid->set_voice_nonlinearity(1.0f);
      psid->sid->get_filter().set_distortion_properties(0.5f, 0.f);
    } else {
      psid->sid->set_chip_model(MOS6581FP);
      psid->sid->set_voice_nonlinearity(0.96f);
      psid->sid->get_filter().set_distortion_properties(0.50f, 3.3e6f);
    }

    switch (model) {

    case SID_MODEL_8580R5_3691:
      psid->sid->get_filter().set_type4_properties(6.55f, 20.0f);
      strcpy(model_text, "8580R5 3691");
      break;
    case SID_MODEL_8580R5_3691D:
      psid->sid->get_filter().set_type4_properties(6.55f, 20.0f);
      psid->sid->input(-32768);
      strcpy(model_text, "8580R5 3691 + digi boost");
      break;

    case SID_MODEL_8580R5_1489:
      psid->sid->get_filter().set_type4_properties(5.7f, 20.0f);
      strcpy(model_text, "8580R5 1489");
      break;
    case SID_MODEL_8580R5_1489D:
      psid->sid->get_filter().set_type4_properties(5.7f, 20.0f);
      psid->sid->input(-32768);
      strcpy(model_text, "8580R5 1489 + digi boost");
      break;

    case SID_MODEL_6581R3_4885:
      psid->sid->get_filter().set_type3_properties(840577.4520801408f, 1909158.8633669745f, 1.0068865662510837f, 14858.140079688419f);
      strcpy(model_text, "6581R3 4885");
      break;
    case SID_MODEL_6581R3_0486S:
      psid->sid->get_filter().set_type3_properties(1164920.4999651583f, 12915042.165290257f, 1.0058853753357735f, 12914.5661141159f);
      strcpy(model_text, "6581R3 0486S");
      break;
    case SID_MODEL_6581R3_3984:
      psid->sid->get_filter().set_type3_properties(1522171.922983084f, 21729926.667291082f, 1.004994802537475f, 14299.149638099827f);
      strcpy(model_text, "6581R3 3984");
      break;
    default:
    case SID_MODEL_6581R4AR_3789:
      psid->sid->get_filter().set_type3_properties(1141069.9277645703f, 276016753.85303545f, 1.0066634233403395f, 16402.86712485317f);
      strcpy(model_text, "6581R4AR 3789");
      break;
    case SID_MODEL_6581R3_4485:
      psid->sid->get_filter().set_type3_properties(1399768.3253307983f, 553018906.8926692f, 1.0051493199361266f, 11961.908870403166f);
      strcpy(model_text, "6581R3 4485");
      break;
    case SID_MODEL_6581R4_1986S:
      psid->sid->get_filter().set_type3_properties(1250736.2235895505f, 1521187976.8735676f, 1.005543646897986f, 8581.78418415723f);
      strcpy(model_text, "6581R4 1986S");
      break;
    }

    psid->sid->enable_filter(filters_enabled ? true : false);

    switch (sampling) {
      default:
      case 1:
        method = SAMPLE_INTERPOLATE;
        strcpy(method_text, "interpolation");
        break;
      case 2:
      case 3:
        method = SAMPLE_RESAMPLE_INTERPOLATE;
        sprintf(method_text, "%sresampling, cutoff %d Hz",
                             (psid->sid->sse_enabled() ? "SSE " : ""),
                             (int) (passband > 20000.f ? 20000.f : passband));
        break;
    }

    //! \todo FIXME: These casts have to go away
    if (!psid->sid->set_sampling_parameters((float)cycles_per_sec, method,
                                            (float)speed, passband)) {
        log_warning(LOG_DEFAULT,
                    "ReSID-FP: unable to set sampling mode; try increasing sampling frequency to 44.1-48 kHz and keep passband around 80-90 %%.");
        return 0;
    }

    log_message(LOG_DEFAULT,
                "ReSID-FP: %s, filter %s, sampling rate %d Hz with %s",
                model_text,
                filters_enabled ? "on" : "off",
                speed,
                method_text);
    return 1;
}