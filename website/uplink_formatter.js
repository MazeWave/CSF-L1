function decodeUplink(input) {
    devid   = input.bytes[0]
    motions = input.bytes[1] | 0
    return {
      data: {
        devid  : devid,
        motions: motions
      },
      warnings: [],
      errors: []
    };
  }